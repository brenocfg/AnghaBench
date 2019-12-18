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
struct i2400m_tlv_hdr {int dummy; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum i2400m_tlv { ____Placeholder_i2400m_tlv } i2400m_tlv ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,scalar_t__,scalar_t__) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 struct i2400m_tlv_hdr* i2400m_tlv_buffer_walk (struct i2400m*,struct i2400m_tlv_hdr const*,size_t,struct i2400m_tlv_hdr const*) ; 
 scalar_t__ i2400m_tlv_match (struct i2400m_tlv_hdr const*,int,scalar_t__) ; 

__attribute__((used)) static
const struct i2400m_tlv_hdr *i2400m_tlv_find(
	struct i2400m *i2400m,
	const struct i2400m_tlv_hdr *tlv_hdr, size_t size,
	enum i2400m_tlv tlv_type, ssize_t tlv_size)
{
	ssize_t match;
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_tlv_hdr *tlv = NULL;
	while ((tlv = i2400m_tlv_buffer_walk(i2400m, tlv_hdr, size, tlv))) {
		match = i2400m_tlv_match(tlv, tlv_type, tlv_size);
		if (match == 0)		/* found it :) */
			break;
		if (match > 0)
			dev_warn(dev, "TLV type 0x%04x found with size "
				 "mismatch (%zu vs %zd needed)\n",
				 tlv_type, match, tlv_size);
	}
	return tlv;
}