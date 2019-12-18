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
typedef  int /*<<< orphan*/  u8 ;
struct ams_delta_nand {int /*<<< orphan*/  data_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  ams_delta_dir_input (struct ams_delta_nand*) ; 
 int /*<<< orphan*/  ams_delta_io_read (struct ams_delta_nand*) ; 

__attribute__((used)) static void ams_delta_read_buf(struct ams_delta_nand *priv, u8 *buf, int len)
{
	int i;

	if (!priv->data_in)
		ams_delta_dir_input(priv);

	for (i = 0; i < len; i++)
		buf[i] = ams_delta_io_read(priv);
}