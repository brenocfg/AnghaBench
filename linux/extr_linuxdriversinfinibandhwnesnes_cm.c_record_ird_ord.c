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
typedef  scalar_t__ u16 ;
struct nes_cm_node {scalar_t__ ord_size; scalar_t__ ird_size; } ;

/* Variables and functions */
 scalar_t__ NES_MAX_IRD ; 
 scalar_t__ NES_MAX_ORD ; 

__attribute__((used)) static void record_ird_ord(struct nes_cm_node *cm_node,
					u16 conn_ird, u16 conn_ord)
{
	if (conn_ird > NES_MAX_IRD)
		conn_ird = NES_MAX_IRD;

	if (conn_ord > NES_MAX_ORD)
		conn_ord = NES_MAX_ORD;

	cm_node->ird_size = conn_ird;
	cm_node->ord_size = conn_ord;
}