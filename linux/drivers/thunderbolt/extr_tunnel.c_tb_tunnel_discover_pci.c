#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tb_tunnel {struct tb_port* dst_port; struct tb_port* src_port; struct tb_path** paths; int /*<<< orphan*/  activate; } ;
struct tb_port {int dummy; } ;
struct tb_path {int dummy; } ;
struct tb {int dummy; } ;

/* Variables and functions */
 int TB_PCI_HOPID ; 
 size_t TB_PCI_PATH_DOWN ; 
 size_t TB_PCI_PATH_UP ; 
 int /*<<< orphan*/  TB_TUNNEL_PCI ; 
 struct tb_path* tb_path_discover (struct tb_port*,int,struct tb_port*,int,struct tb_port**,char*) ; 
 int /*<<< orphan*/  tb_pci_activate ; 
 int /*<<< orphan*/  tb_pci_init_path (struct tb_path*) ; 
 int /*<<< orphan*/  tb_pci_port_enable (struct tb_port*,int) ; 
 int /*<<< orphan*/  tb_pci_port_is_enabled (struct tb_port*) ; 
 int /*<<< orphan*/  tb_port_is_pcie_up (struct tb_port*) ; 
 int /*<<< orphan*/  tb_port_warn (struct tb_port*,char*) ; 
 struct tb_tunnel* tb_tunnel_alloc (struct tb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_tunnel_dbg (struct tb_tunnel*,char*) ; 
 int /*<<< orphan*/  tb_tunnel_deactivate (struct tb_tunnel*) ; 
 int /*<<< orphan*/  tb_tunnel_free (struct tb_tunnel*) ; 
 int /*<<< orphan*/  tb_tunnel_warn (struct tb_tunnel*,char*) ; 

struct tb_tunnel *tb_tunnel_discover_pci(struct tb *tb, struct tb_port *down)
{
	struct tb_tunnel *tunnel;
	struct tb_path *path;

	if (!tb_pci_port_is_enabled(down))
		return NULL;

	tunnel = tb_tunnel_alloc(tb, 2, TB_TUNNEL_PCI);
	if (!tunnel)
		return NULL;

	tunnel->activate = tb_pci_activate;
	tunnel->src_port = down;

	/*
	 * Discover both paths even if they are not complete. We will
	 * clean them up by calling tb_tunnel_deactivate() below in that
	 * case.
	 */
	path = tb_path_discover(down, TB_PCI_HOPID, NULL, -1,
				&tunnel->dst_port, "PCIe Up");
	if (!path) {
		/* Just disable the downstream port */
		tb_pci_port_enable(down, false);
		goto err_free;
	}
	tunnel->paths[TB_PCI_PATH_UP] = path;
	tb_pci_init_path(tunnel->paths[TB_PCI_PATH_UP]);

	path = tb_path_discover(tunnel->dst_port, -1, down, TB_PCI_HOPID, NULL,
				"PCIe Down");
	if (!path)
		goto err_deactivate;
	tunnel->paths[TB_PCI_PATH_DOWN] = path;
	tb_pci_init_path(tunnel->paths[TB_PCI_PATH_DOWN]);

	/* Validate that the tunnel is complete */
	if (!tb_port_is_pcie_up(tunnel->dst_port)) {
		tb_port_warn(tunnel->dst_port,
			     "path does not end on a PCIe adapter, cleaning up\n");
		goto err_deactivate;
	}

	if (down != tunnel->src_port) {
		tb_tunnel_warn(tunnel, "path is not complete, cleaning up\n");
		goto err_deactivate;
	}

	if (!tb_pci_port_is_enabled(tunnel->dst_port)) {
		tb_tunnel_warn(tunnel,
			       "tunnel is not fully activated, cleaning up\n");
		goto err_deactivate;
	}

	tb_tunnel_dbg(tunnel, "discovered\n");
	return tunnel;

err_deactivate:
	tb_tunnel_deactivate(tunnel);
err_free:
	tb_tunnel_free(tunnel);

	return NULL;
}