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
typedef  int u8 ;
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_CMD_PLANES_STATUS ; 
 int /*<<< orphan*/  DOC_SEQ_PLANES_STATUS ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_ecc_disable (struct docg3*) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_read_data_area (struct docg3*,int*,int,int) ; 

__attribute__((used)) static int doc_get_op_status(struct docg3 *docg3)
{
	u8 status;

	doc_flash_sequence(docg3, DOC_SEQ_PLANES_STATUS);
	doc_flash_command(docg3, DOC_CMD_PLANES_STATUS);
	doc_delay(docg3, 5);

	doc_ecc_disable(docg3);
	doc_read_data_area(docg3, &status, 1, 1);
	return status;
}