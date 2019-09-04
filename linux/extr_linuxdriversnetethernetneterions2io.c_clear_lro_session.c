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
typedef  int u16 ;
struct lro {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct lro*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_lro_session(struct lro *lro)
{
	static u16 lro_struct_size = sizeof(struct lro);

	memset(lro, 0, lro_struct_size);
}