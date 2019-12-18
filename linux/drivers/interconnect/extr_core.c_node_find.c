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
struct icc_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icc_idr ; 
 struct icc_node* idr_find (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static struct icc_node *node_find(const int id)
{
	return idr_find(&icc_idr, id);
}