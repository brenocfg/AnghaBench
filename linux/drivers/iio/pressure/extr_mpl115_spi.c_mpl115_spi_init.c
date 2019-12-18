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
struct spi_device {int dummy; } ;
struct mpl115_spi_buf {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mpl115_spi_buf* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mpl115_spi_buf*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int mpl115_spi_init(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);
	struct mpl115_spi_buf *buf;

	buf = devm_kzalloc(dev, sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	spi_set_drvdata(spi, buf);

	return 0;
}