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
 unsigned int CARL9170FW_MAX_SIZE ; 
 unsigned int CARL9170FW_MIN_SIZE ; 

__attribute__((used)) static inline bool carl9170fw_size_check(unsigned int len)
{
	return (len <= CARL9170FW_MAX_SIZE && len >= CARL9170FW_MIN_SIZE);
}