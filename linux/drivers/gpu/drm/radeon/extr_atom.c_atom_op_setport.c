#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_4__ {int io_mode; } ;

/* Variables and functions */
 int ATOM_IO_IIO ; 
 int ATOM_IO_MM ; 
 int ATOM_IO_NAMES_CNT ; 
 int ATOM_IO_PCI ; 
 int ATOM_IO_SYSIO ; 
#define  ATOM_PORT_ATI 130 
#define  ATOM_PORT_PCI 129 
#define  ATOM_PORT_SYSIO 128 
 int /*<<< orphan*/  SDEBUG (char*,int,...) ; 
 int U16 (int) ; 
 int /*<<< orphan*/ * atom_io_names ; 

__attribute__((used)) static void atom_op_setport(atom_exec_context *ctx, int *ptr, int arg)
{
	int port;
	switch (arg) {
	case ATOM_PORT_ATI:
		port = U16(*ptr);
		if (port < ATOM_IO_NAMES_CNT)
			SDEBUG("   port: %d (%s)\n", port, atom_io_names[port]);
		else
			SDEBUG("   port: %d\n", port);
		if (!port)
			ctx->ctx->io_mode = ATOM_IO_MM;
		else
			ctx->ctx->io_mode = ATOM_IO_IIO | port;
		(*ptr) += 2;
		break;
	case ATOM_PORT_PCI:
		ctx->ctx->io_mode = ATOM_IO_PCI;
		(*ptr)++;
		break;
	case ATOM_PORT_SYSIO:
		ctx->ctx->io_mode = ATOM_IO_SYSIO;
		(*ptr)++;
		break;
	}
}