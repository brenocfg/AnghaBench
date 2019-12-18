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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int M48T86_NVRAM (scalar_t__) ; 
 scalar_t__ M48T86_NVRAM_LEN ; 
 int m48t86_readb (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  m48t86_writeb (int /*<<< orphan*/ *,unsigned char,unsigned int) ; 

__attribute__((used)) static bool m48t86_verify_chip(struct platform_device *pdev)
{
	unsigned int offset0 = M48T86_NVRAM(M48T86_NVRAM_LEN - 2);
	unsigned int offset1 = M48T86_NVRAM(M48T86_NVRAM_LEN - 1);
	unsigned char tmp0, tmp1;

	tmp0 = m48t86_readb(&pdev->dev, offset0);
	tmp1 = m48t86_readb(&pdev->dev, offset1);

	m48t86_writeb(&pdev->dev, 0x00, offset0);
	m48t86_writeb(&pdev->dev, 0x55, offset1);
	if (m48t86_readb(&pdev->dev, offset1) == 0x55) {
		m48t86_writeb(&pdev->dev, 0xaa, offset1);
		if (m48t86_readb(&pdev->dev, offset1) == 0xaa &&
		    m48t86_readb(&pdev->dev, offset0) == 0x00) {
			m48t86_writeb(&pdev->dev, tmp0, offset0);
			m48t86_writeb(&pdev->dev, tmp1, offset1);

			return true;
		}
	}
	return false;
}