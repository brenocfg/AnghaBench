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

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int ENCODER_STREAM_OFFSET ; 
 int /*<<< orphan*/  SIZE_MACROBLOCK ; 
 unsigned int SZ_256 ; 
 unsigned int round_up (unsigned int,int) ; 

__attribute__((used)) static unsigned int estimate_stream_size(unsigned int width,
					 unsigned int height)
{
	unsigned int offset = ENCODER_STREAM_OFFSET;
	unsigned int num_blocks = DIV_ROUND_UP(width, SIZE_MACROBLOCK) *
					DIV_ROUND_UP(height, SIZE_MACROBLOCK);
	unsigned int pcm_size = SZ_256;
	unsigned int partition_table = SZ_256;

	return round_up(offset + num_blocks * pcm_size + partition_table, 32);
}