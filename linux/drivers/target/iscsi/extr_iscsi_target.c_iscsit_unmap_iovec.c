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
typedef  size_t u32 ;
struct scatterlist {int dummy; } ;
struct iscsi_cmd {size_t kmapped_nents; struct scatterlist* first_data_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void iscsit_unmap_iovec(struct iscsi_cmd *cmd)
{
	u32 i;
	struct scatterlist *sg;

	sg = cmd->first_data_sg;

	for (i = 0; i < cmd->kmapped_nents; i++)
		kunmap(sg_page(&sg[i]));
}