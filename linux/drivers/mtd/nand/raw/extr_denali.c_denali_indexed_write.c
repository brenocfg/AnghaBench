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
struct denali_controller {scalar_t__ host; } ;

/* Variables and functions */
 scalar_t__ DENALI_INDEXED_CTRL ; 
 scalar_t__ DENALI_INDEXED_DATA ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void denali_indexed_write(struct denali_controller *denali, u32 addr,
				 u32 data)
{
	iowrite32(addr, denali->host + DENALI_INDEXED_CTRL);
	iowrite32(data, denali->host + DENALI_INDEXED_DATA);
}