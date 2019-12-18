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
struct qla27xx_image_status {int /*<<< orphan*/  generation; } ;
typedef  int int16_t ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_init ; 

__attribute__((used)) static int
qla27xx_compare_image_generation(
    struct qla27xx_image_status *pri_image_status,
    struct qla27xx_image_status *sec_image_status)
{
	/* calculate generation delta as uint16 (this accounts for wrap) */
	int16_t delta =
	    le16_to_cpu(pri_image_status->generation) -
	    le16_to_cpu(sec_image_status->generation);

	ql_dbg(ql_dbg_init, NULL, 0x0180, "generation delta = %d\n", delta);

	return delta;
}