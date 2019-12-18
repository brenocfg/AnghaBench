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
struct aidaw {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static inline unsigned long scm_aidaw_bytes(struct aidaw *aidaw)
{
	unsigned long _aidaw = (unsigned long) aidaw;
	unsigned long bytes = ALIGN(_aidaw, PAGE_SIZE) - _aidaw;

	return (bytes / sizeof(*aidaw)) * PAGE_SIZE;
}