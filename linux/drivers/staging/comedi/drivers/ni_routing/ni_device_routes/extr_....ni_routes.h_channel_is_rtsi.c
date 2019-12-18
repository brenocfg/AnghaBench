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

/* Variables and functions */
 int TRIGGER_LINE (int) ; 

__attribute__((used)) static inline bool channel_is_rtsi(int channel)
{
	return TRIGGER_LINE(0) <= channel && channel <= TRIGGER_LINE(-1);
}