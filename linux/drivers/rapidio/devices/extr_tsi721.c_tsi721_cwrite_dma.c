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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tsi721_device {int dummy; } ;
struct rio_mport {int /*<<< orphan*/  sys_size; struct tsi721_device* priv; } ;

/* Variables and functions */
 int tsi721_maint_dma (struct tsi721_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tsi721_cwrite_dma(struct rio_mport *mport, int index, u16 destid,
			 u8 hopcount, u32 offset, int len, u32 data)
{
	struct tsi721_device *priv = mport->priv;
	u32 temp = data;

	return tsi721_maint_dma(priv, mport->sys_size, destid, hopcount,
				offset, len, &temp, 1);
}