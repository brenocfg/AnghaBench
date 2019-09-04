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
 int EINVAL ; 
 int strlen (char*) ; 

__attribute__((used)) static int get_key_size(char **key_string)
{
	return (*key_string[0] == ':') ? -EINVAL : strlen(*key_string) >> 1;
}