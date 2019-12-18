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
struct hantro_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hantro_reset_encoded_fmt (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_reset_raw_fmt (struct hantro_ctx*) ; 

void hantro_reset_fmts(struct hantro_ctx *ctx)
{
	hantro_reset_encoded_fmt(ctx);
	hantro_reset_raw_fmt(ctx);
}