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
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 

__attribute__((used)) static inline void
BEGIN_NIC0(struct nouveau_channel *chan, int subc, int mthd, int size)
{
	OUT_RING(chan, 0x60000000 | (size << 16) | (subc << 13) | (mthd >> 2));
}