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
typedef  int u32 ;
struct unicam_fmt {int depth; } ;

/* Variables and functions */
 unsigned int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPL_ALIGNMENT ; 

__attribute__((used)) static inline unsigned int bytes_per_line(u32 width,
					  const struct unicam_fmt *fmt)
{
	return ALIGN((width * fmt->depth) >> 3, BPL_ALIGNMENT);
}