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
typedef  unsigned int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_CURRENT ; 
 int /*<<< orphan*/  make_field (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_first_field (char*,int /*<<< orphan*/ ) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 

int ps3_repository_read_vuart_av_port(unsigned int *port)
{
	int result;
	u64 v1 = 0;

	result = read_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("vir_uart", 0),
		make_field("port", 0),
		make_field("avset", 0),
		&v1, NULL);
	*port = v1;
	return result;
}