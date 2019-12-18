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
struct iova_magazine {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ IOVA_MAG_SIZE ; 

__attribute__((used)) static bool iova_magazine_full(struct iova_magazine *mag)
{
	return (mag && mag->size == IOVA_MAG_SIZE);
}