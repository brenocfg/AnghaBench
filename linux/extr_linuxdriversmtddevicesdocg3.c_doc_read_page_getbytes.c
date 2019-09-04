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
typedef  int /*<<< orphan*/  u_char ;
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_read_data_area (struct docg3*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int doc_read_page_getbytes(struct docg3 *docg3, int len, u_char *buf,
				  int first, int last_odd)
{
	if (last_odd && len > 0) {
		doc_read_data_area(docg3, buf, 1, first);
		doc_read_data_area(docg3, buf ? buf + 1 : buf, len - 1, 0);
	} else {
		doc_read_data_area(docg3, buf, len, first);
	}
	doc_delay(docg3, 2);
	return len;
}