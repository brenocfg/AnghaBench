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
 int /*<<< orphan*/  cont_thread_id ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_thread_id_continue(char *put_str, char *arg)
{
	char *ptr = &put_str[11];

	if (put_str[1] != 'T' || put_str[2] != '0')
		return 1;
	kgdb_hex2long(&ptr, &cont_thread_id);
	return 0;
}