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
struct tc358743_state {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int tc358743_probe_of(struct tc358743_state *state)
{
	return -ENODEV;
}