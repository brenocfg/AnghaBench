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
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sii8620_mt_read_devcap (struct sii8620*,int) ; 

__attribute__((used)) static void sii8620_got_xdevcap(struct sii8620 *ctx, int ret)
{
	if (ret < 0)
		return;

	sii8620_mt_read_devcap(ctx, false);
}