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
struct stimx274 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx274_start_2 ; 
 int /*<<< orphan*/  imx274_start_3 ; 
 int imx274_write_table (struct stimx274*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_range (int) ; 

__attribute__((used)) static int imx274_start_stream(struct stimx274 *priv)
{
	int err = 0;

	/*
	 * Refer to "Standby Cancel Sequence when using CSI-2" in
	 * imx274 datasheet, it should wait 10ms or more here.
	 * give it 1 extra ms for margin
	 */
	msleep_range(11);
	err = imx274_write_table(priv, imx274_start_2);
	if (err)
		return err;

	/*
	 * Refer to "Standby Cancel Sequence when using CSI-2" in
	 * imx274 datasheet, it should wait 7ms or more here.
	 * give it 1 extra ms for margin
	 */
	msleep_range(8);
	err = imx274_write_table(priv, imx274_start_3);
	if (err)
		return err;

	return 0;
}