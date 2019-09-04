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
 int /*<<< orphan*/  WARN_ON (size_t) ; 
 int /*<<< orphan*/  memchr_inv (void const*,int,size_t) ; 

__attribute__((used)) static bool is_full_mask(const void *p, size_t len)
{
	WARN_ON(len % 4);

	return !memchr_inv(p, 0xff, len);
}