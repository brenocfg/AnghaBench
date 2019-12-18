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
typedef  int u64 ;
struct fastrpc_invoke_ctx {int nscalars; TYPE_2__* olaps; TYPE_1__* args; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ mstart; scalar_t__ mend; } ;
struct TYPE_3__ {int fd; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FASTRPC_ALIGN ; 

__attribute__((used)) static u64 fastrpc_get_payload_size(struct fastrpc_invoke_ctx *ctx, int metalen)
{
	u64 size = 0;
	int i;

	size = ALIGN(metalen, FASTRPC_ALIGN);
	for (i = 0; i < ctx->nscalars; i++) {
		if (ctx->args[i].fd == 0 || ctx->args[i].fd == -1) {

			if (ctx->olaps[i].offset == 0)
				size = ALIGN(size, FASTRPC_ALIGN);

			size += (ctx->olaps[i].mend - ctx->olaps[i].mstart);
		}
	}

	return size;
}