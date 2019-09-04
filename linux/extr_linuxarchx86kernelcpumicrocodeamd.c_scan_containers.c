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
typedef  int /*<<< orphan*/  u8 ;
struct cont_desc {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ parse_container (int /*<<< orphan*/ *,scalar_t__,struct cont_desc*) ; 

__attribute__((used)) static void scan_containers(u8 *ucode, size_t size, struct cont_desc *desc)
{
	ssize_t rem = size;

	while (rem >= 0) {
		ssize_t s = parse_container(ucode, rem, desc);
		if (!s)
			return;

		ucode += s;
		rem   -= s;
	}
}