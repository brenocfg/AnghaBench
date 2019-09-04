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
struct compressor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_DCE110_COMPRESSOR (struct compressor*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void dce110_compressor_destroy(struct compressor **compressor)
{
	kfree(TO_DCE110_COMPRESSOR(*compressor));
	*compressor = NULL;
}