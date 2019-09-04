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
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_MSC_MSG_RCPK ; 
 int /*<<< orphan*/  sii8620_mt_msc_msg (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_mt_rcpk(struct sii8620 *ctx, u8 code)
{
	sii8620_mt_msc_msg(ctx, MHL_MSC_MSG_RCPK, code);
}