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
struct tgfx {scalar_t__ parportno; int /*<<< orphan*/  pd; scalar_t__* dev; } ;
struct parport {scalar_t__ number; } ;

/* Variables and functions */
 int TGFX_MAX_DEVICES ; 
 int TGFX_MAX_PORTS ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct tgfx*) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 struct tgfx** tgfx_base ; 

__attribute__((used)) static void tgfx_detach(struct parport *port)
{
	int i;
	struct tgfx *tgfx;

	for (i = 0; i < TGFX_MAX_PORTS; i++) {
		if (tgfx_base[i] && tgfx_base[i]->parportno == port->number)
			break;
	}

	if (i == TGFX_MAX_PORTS)
		return;

	tgfx = tgfx_base[i];
	tgfx_base[i] = NULL;

	for (i = 0; i < TGFX_MAX_DEVICES; i++)
		if (tgfx->dev[i])
			input_unregister_device(tgfx->dev[i]);
	parport_unregister_device(tgfx->pd);
	kfree(tgfx);
}