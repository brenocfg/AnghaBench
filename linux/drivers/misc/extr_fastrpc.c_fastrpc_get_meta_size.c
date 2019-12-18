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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct fastrpc_remote_arg {int dummy; } ;
struct fastrpc_phy_page {int dummy; } ;
struct fastrpc_invoke_ctx {int nscalars; } ;
struct fastrpc_invoke_buf {int dummy; } ;

/* Variables and functions */
 int FASTRPC_MAX_CRCLIST ; 
 int FASTRPC_MAX_FDLIST ; 

__attribute__((used)) static int fastrpc_get_meta_size(struct fastrpc_invoke_ctx *ctx)
{
	int size = 0;

	size = (sizeof(struct fastrpc_remote_arg) +
		sizeof(struct fastrpc_invoke_buf) +
		sizeof(struct fastrpc_phy_page)) * ctx->nscalars +
		sizeof(u64) * FASTRPC_MAX_FDLIST +
		sizeof(u32) * FASTRPC_MAX_CRCLIST;

	return size;
}