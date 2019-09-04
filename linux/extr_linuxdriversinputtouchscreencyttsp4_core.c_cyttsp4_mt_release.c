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
struct cyttsp4_mt_data {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyttsp4_mt_release(struct cyttsp4_mt_data *md)
{
	input_unregister_device(md->input);
	input_set_drvdata(md->input, NULL);
}