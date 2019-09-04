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
struct ad714x_chip {int /*<<< orphan*/  (* write ) (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short) ;int /*<<< orphan*/  (* read ) (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  STG_COM_INT_EN_REG ; 
 int /*<<< orphan*/  STG_HIGH_INT_EN_REG ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short*,int) ; 
 int /*<<< orphan*/  stub2 (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  stub3 (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short*,int) ; 
 int /*<<< orphan*/  stub4 (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void ad714x_use_thr_int(struct ad714x_chip *ad714x,
				int start_stage, int end_stage)
{
	unsigned short data;
	unsigned short mask;

	mask = ((1 << (end_stage + 1)) - 1) - ((1 << start_stage) - 1);

	ad714x->read(ad714x, STG_COM_INT_EN_REG, &data, 1);
	data &= ~(1 << end_stage);
	ad714x->write(ad714x, STG_COM_INT_EN_REG, data);

	ad714x->read(ad714x, STG_HIGH_INT_EN_REG, &data, 1);
	data |= mask;
	ad714x->write(ad714x, STG_HIGH_INT_EN_REG, data);
}