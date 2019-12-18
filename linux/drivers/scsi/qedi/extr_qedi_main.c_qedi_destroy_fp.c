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
struct qedi_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qedi_free_fp (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_free_sb (struct qedi_ctx*) ; 

__attribute__((used)) static void qedi_destroy_fp(struct qedi_ctx *qedi)
{
	qedi_free_sb(qedi);
	qedi_free_fp(qedi);
}