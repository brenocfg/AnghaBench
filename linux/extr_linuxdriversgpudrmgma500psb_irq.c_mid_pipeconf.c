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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  PIPEACONF ; 
 int /*<<< orphan*/  PIPEBCONF ; 
 int /*<<< orphan*/  PIPECCONF ; 

__attribute__((used)) static inline u32
mid_pipeconf(int pipe)
{
	if (pipe == 0)
		return PIPEACONF;
	if (pipe == 1)
		return PIPEBCONF;
	if (pipe == 2)
		return PIPECCONF;
	BUG();
}