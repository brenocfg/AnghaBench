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
struct s6e3ha2 {TYPE_1__* desc; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ HA2_TYPE ; 
 scalar_t__ HF2_TYPE ; 
 int /*<<< orphan*/  s6e3ha2_dcs_write_seq_static (struct s6e3ha2*,int,int,...) ; 

__attribute__((used)) static int s6e3ha2_freq_calibration(struct s6e3ha2 *ctx)
{
	s6e3ha2_dcs_write_seq_static(ctx, 0xfd, 0x1c);
	if (ctx->desc->type == HF2_TYPE)
		s6e3ha2_dcs_write_seq_static(ctx, 0xf2, 0x67, 0x40, 0xc5);
	s6e3ha2_dcs_write_seq_static(ctx, 0xfe, 0x20, 0x39);
	s6e3ha2_dcs_write_seq_static(ctx, 0xfe, 0xa0);
	s6e3ha2_dcs_write_seq_static(ctx, 0xfe, 0x20);

	if (ctx->desc->type == HA2_TYPE)
		s6e3ha2_dcs_write_seq_static(ctx, 0xce, 0x03, 0x3b, 0x12, 0x62,
						  0x40, 0x80, 0xc0, 0x28, 0x28,
						  0x28, 0x28, 0x39, 0xc5);
	else
		s6e3ha2_dcs_write_seq_static(ctx, 0xce, 0x03, 0x3b, 0x14, 0x6d,
						  0x40, 0x80, 0xc0, 0x28, 0x28,
						  0x28, 0x28, 0x39, 0xc5);

	return 0;
}