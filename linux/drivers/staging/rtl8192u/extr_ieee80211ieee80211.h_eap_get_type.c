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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 char const** eap_types ; 

__attribute__((used)) static inline const char *eap_get_type(int type)
{
	return ((u32)type >= ARRAY_SIZE(eap_types)) ? "Unknown" : eap_types[type];
}