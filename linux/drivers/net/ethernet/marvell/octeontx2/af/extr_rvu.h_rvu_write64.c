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
typedef  int u64 ;
struct rvu {scalar_t__ afreg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static inline void rvu_write64(struct rvu *rvu, u64 block, u64 offset, u64 val)
{
	writeq(val, rvu->afreg_base + ((block << 28) | offset));
}