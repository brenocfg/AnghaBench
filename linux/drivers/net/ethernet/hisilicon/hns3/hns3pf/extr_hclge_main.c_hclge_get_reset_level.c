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
struct hnae3_ae_dev {struct hclge_dev* priv; } ;
struct hclge_dev {scalar_t__ reset_type; int /*<<< orphan*/  misc_vector; } ;
typedef  enum hnae3_reset_type { ____Placeholder_hnae3_reset_type } hnae3_reset_type ;

/* Variables and functions */
 int HNAE3_FLR_RESET ; 
 int HNAE3_FUNC_RESET ; 
 int HNAE3_GLOBAL_RESET ; 
 int HNAE3_IMP_RESET ; 
 scalar_t__ HNAE3_NONE_RESET ; 
 int HNAE3_UNKNOWN_RESET ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  hclge_enable_vector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hclge_handle_hw_msix_error (struct hclge_dev*,unsigned long*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static enum hnae3_reset_type hclge_get_reset_level(struct hnae3_ae_dev *ae_dev,
						   unsigned long *addr)
{
	enum hnae3_reset_type rst_level = HNAE3_NONE_RESET;
	struct hclge_dev *hdev = ae_dev->priv;

	/* first, resolve any unknown reset type to the known type(s) */
	if (test_bit(HNAE3_UNKNOWN_RESET, addr)) {
		/* we will intentionally ignore any errors from this function
		 *  as we will end up in *some* reset request in any case
		 */
		hclge_handle_hw_msix_error(hdev, addr);
		clear_bit(HNAE3_UNKNOWN_RESET, addr);
		/* We defered the clearing of the error event which caused
		 * interrupt since it was not posssible to do that in
		 * interrupt context (and this is the reason we introduced
		 * new UNKNOWN reset type). Now, the errors have been
		 * handled and cleared in hardware we can safely enable
		 * interrupts. This is an exception to the norm.
		 */
		hclge_enable_vector(&hdev->misc_vector, true);
	}

	/* return the highest priority reset level amongst all */
	if (test_bit(HNAE3_IMP_RESET, addr)) {
		rst_level = HNAE3_IMP_RESET;
		clear_bit(HNAE3_IMP_RESET, addr);
		clear_bit(HNAE3_GLOBAL_RESET, addr);
		clear_bit(HNAE3_FUNC_RESET, addr);
	} else if (test_bit(HNAE3_GLOBAL_RESET, addr)) {
		rst_level = HNAE3_GLOBAL_RESET;
		clear_bit(HNAE3_GLOBAL_RESET, addr);
		clear_bit(HNAE3_FUNC_RESET, addr);
	} else if (test_bit(HNAE3_FUNC_RESET, addr)) {
		rst_level = HNAE3_FUNC_RESET;
		clear_bit(HNAE3_FUNC_RESET, addr);
	} else if (test_bit(HNAE3_FLR_RESET, addr)) {
		rst_level = HNAE3_FLR_RESET;
		clear_bit(HNAE3_FLR_RESET, addr);
	}

	if (hdev->reset_type != HNAE3_NONE_RESET &&
	    rst_level < hdev->reset_type)
		return HNAE3_NONE_RESET;

	return rst_level;
}