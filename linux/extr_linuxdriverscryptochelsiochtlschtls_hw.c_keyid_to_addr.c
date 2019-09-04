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
 int TLS_KEY_CONTEXT_SZ ; 

unsigned int keyid_to_addr(int start_addr, int keyid)
{
	return (start_addr + (keyid * TLS_KEY_CONTEXT_SZ)) >> 5;
}