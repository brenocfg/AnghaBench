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
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_IMASK ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __b44_disable_ints(struct b44 *bp)
{
	bw32(bp, B44_IMASK, 0);
}