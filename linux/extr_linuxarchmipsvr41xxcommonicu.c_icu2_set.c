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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  icu2_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t icu2_set(uint8_t offset, uint16_t set)
{
	uint16_t data;

	data = icu2_read(offset);
	data |= set;
	icu2_write(offset, data);

	return data;
}