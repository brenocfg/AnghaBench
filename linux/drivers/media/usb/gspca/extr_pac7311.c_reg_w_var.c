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
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
#define  END_OF_SEQUENCE 129 
#define  LOAD_PAGE4 128 
 int USB_BUF_SZ ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  reg_w_page (struct gspca_dev*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void reg_w_var(struct gspca_dev *gspca_dev,
			const __u8 *seq,
			const __u8 *page4, unsigned int page4_len)
{
	int index, len;

	for (;;) {
		index = *seq++;
		len = *seq++;
		switch (len) {
		case END_OF_SEQUENCE:
			return;
		case LOAD_PAGE4:
			reg_w_page(gspca_dev, page4, page4_len);
			break;
		default:
			if (len > USB_BUF_SZ) {
				gspca_err(gspca_dev, "Incorrect variable sequence\n");
				return;
			}
			while (len > 0) {
				if (len < 8) {
					reg_w_buf(gspca_dev,
						index, seq, len);
					seq += len;
					break;
				}
				reg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				len -= 8;
			}
		}
	}
	/* not reached */
}