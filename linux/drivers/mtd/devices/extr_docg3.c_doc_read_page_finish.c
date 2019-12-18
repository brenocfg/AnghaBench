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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  doc_page_finish (struct docg3*) ; 
 int /*<<< orphan*/  doc_set_device_id (struct docg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_read_page_finish(struct docg3 *docg3)
{
	doc_page_finish(docg3);
	doc_set_device_id(docg3, 0);
}