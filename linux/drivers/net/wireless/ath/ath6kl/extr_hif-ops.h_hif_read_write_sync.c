#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {int (* read_write_sync ) (struct ath6kl*,int,int /*<<< orphan*/ *,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HIF ; 
 int HIF_WRITE ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *,int,int) ; 
 int stub1 (struct ath6kl*,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int hif_read_write_sync(struct ath6kl *ar, u32 addr, u8 *buf,
				      u32 len, u32 request)
{
	ath6kl_dbg(ATH6KL_DBG_HIF,
		   "hif %s sync addr 0x%x buf 0x%p len %d request 0x%x\n",
		   (request & HIF_WRITE) ? "write" : "read",
		   addr, buf, len, request);

	return ar->hif_ops->read_write_sync(ar, addr, buf, len, request);
}