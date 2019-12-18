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
struct qeth_cmd_buffer {int /*<<< orphan*/  length; scalar_t__ data; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct ccw1 *__ccw_from_cmd(struct qeth_cmd_buffer *iob)
{
	return (struct ccw1 *)(iob->data + ALIGN(iob->length, 8));
}