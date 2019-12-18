#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vga_switcheroo_client {int /*<<< orphan*/  pdev; TYPE_1__* ops; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_4__ {int /*<<< orphan*/  clients; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_gpu_state ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ID_BIT_AUDIO ; 
 struct vga_switcheroo_client* find_client_from_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ vgasr_priv ; 

__attribute__((used)) static void set_audio_state(enum vga_switcheroo_client_id id,
			    enum vga_switcheroo_state state)
{
	struct vga_switcheroo_client *client;

	client = find_client_from_id(&vgasr_priv.clients, id | ID_BIT_AUDIO);
	if (client)
		client->ops->set_gpu_state(client->pdev, state);
}