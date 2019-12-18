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
struct reserved_mem {scalar_t__ size; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ fbpr_a ; 
 scalar_t__ fbpr_sz ; 

__attribute__((used)) static int bman_fbpr(struct reserved_mem *rmem)
{
	fbpr_a = rmem->base;
	fbpr_sz = rmem->size;

	WARN_ON(!(fbpr_a && fbpr_sz));

	return 0;
}