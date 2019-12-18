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
struct r820t_sect_type {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (struct r820t_sect_type,struct r820t_sect_type) ; 

__attribute__((used)) static void r820t_compre_cor(struct r820t_sect_type iq[3])
{
	int i;

	for (i = 3; i > 0; i--) {
		if (iq[0].value > iq[i - 1].value)
			swap(iq[0], iq[i - 1]);
	}
}