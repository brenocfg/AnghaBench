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
struct ams_delta_nand {scalar_t__ data_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  ams_delta_dir_output (struct ams_delta_nand*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ams_delta_io_write (struct ams_delta_nand*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void ams_delta_write_buf(struct ams_delta_nand *priv, const u8 *buf,
				int len)
{
	int i = 0;

	if (len > 0 && priv->data_in)
		ams_delta_dir_output(priv, buf[i++]);

	while (i < len)
		ams_delta_io_write(priv, buf[i++]);
}