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
struct bucket {int dummy; } ;

/* Variables and functions */
 scalar_t__ GC_SECTORS_USED (struct bucket*) ; 

__attribute__((used)) static bool bucket_cmp(struct bucket *l, struct bucket *r)
{
	return GC_SECTORS_USED(l) < GC_SECTORS_USED(r);
}