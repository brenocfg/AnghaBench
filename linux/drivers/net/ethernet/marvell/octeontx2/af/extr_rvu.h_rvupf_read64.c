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
typedef  scalar_t__ u64 ;
struct rvu {scalar_t__ pfreg_base; } ;

/* Variables and functions */
 scalar_t__ readq (scalar_t__) ; 

__attribute__((used)) static inline u64 rvupf_read64(struct rvu *rvu, u64 offset)
{
	return readq(rvu->pfreg_base + offset);
}