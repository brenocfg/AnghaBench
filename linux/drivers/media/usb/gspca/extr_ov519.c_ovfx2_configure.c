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
struct sd {int stopped; } ;
struct ov_regvals {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ov_regvals const*) ; 
 int /*<<< orphan*/  write_regvals (struct sd*,struct ov_regvals const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ovfx2_configure(struct sd *sd)
{
	static const struct ov_regvals init_fx2[] = {
		{ 0x00, 0x60 },
		{ 0x02, 0x01 },
		{ 0x0f, 0x1d },
		{ 0xe9, 0x82 },
		{ 0xea, 0xc7 },
		{ 0xeb, 0x10 },
		{ 0xec, 0xf6 },
	};

	sd->stopped = 1;

	write_regvals(sd, init_fx2, ARRAY_SIZE(init_fx2));
}