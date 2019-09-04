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
struct s5p_cec_dev {int dummy; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 struct s5p_cec_dev* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  s5p_cec_set_addr (struct s5p_cec_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_cec_adap_log_addr(struct cec_adapter *adap, u8 addr)
{
	struct s5p_cec_dev *cec = cec_get_drvdata(adap);

	s5p_cec_set_addr(cec, addr);
	return 0;
}