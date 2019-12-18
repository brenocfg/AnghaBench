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
struct wil6210_priv {int dummy; } ;
struct dentry {int dummy; } ;
struct dbg_off {int type; int /*<<< orphan*/  off; int /*<<< orphan*/  mode; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file_unsafe (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
 int /*<<< orphan*/  debugfs_create_u8 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
 int /*<<< orphan*/  debugfs_create_x32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*) ; 
#define  doff_io32 132 
#define  doff_u32 131 
#define  doff_u8 130 
#define  doff_ulong 129 
#define  doff_x32 128 
 int /*<<< orphan*/  wil_debugfs_create_iomem_x32 (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*,struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_fops_ulong ; 

__attribute__((used)) static void wil6210_debugfs_init_offset(struct wil6210_priv *wil,
					struct dentry *dbg, void *base,
					const struct dbg_off * const tbl)
{
	int i;

	for (i = 0; tbl[i].name; i++) {
		switch (tbl[i].type) {
		case doff_u32:
			debugfs_create_u32(tbl[i].name, tbl[i].mode, dbg,
					   base + tbl[i].off);
			break;
		case doff_x32:
			debugfs_create_x32(tbl[i].name, tbl[i].mode, dbg,
					   base + tbl[i].off);
			break;
		case doff_ulong:
			debugfs_create_file_unsafe(tbl[i].name, tbl[i].mode,
						   dbg, base + tbl[i].off,
						   &wil_fops_ulong);
			break;
		case doff_io32:
			wil_debugfs_create_iomem_x32(tbl[i].name, tbl[i].mode,
						     dbg, base + tbl[i].off,
						     wil);
			break;
		case doff_u8:
			debugfs_create_u8(tbl[i].name, tbl[i].mode, dbg,
					  base + tbl[i].off);
			break;
		}
	}
}