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
struct t4_sq {int flags; } ;

/* Variables and functions */
 int T4_SQ_ONCHIP ; 

__attribute__((used)) static inline int t4_sq_onchip(struct t4_sq *sq)
{
	return sq->flags & T4_SQ_ONCHIP;
}