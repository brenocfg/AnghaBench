#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int cs; int /*<<< orphan*/  bl; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  PS3AV_CMD_AV_CS_8 ; 
 TYPE_1__* ps3av_cs_video2av_table ; 

__attribute__((used)) static u32 ps3av_cs_video2av_bitlen(int cs)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ps3av_cs_video2av_table); i++)
		if (ps3av_cs_video2av_table[i].cs == cs)
			return ps3av_cs_video2av_table[i].bl;

	return PS3AV_CMD_AV_CS_8;
}